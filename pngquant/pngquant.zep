namespace Pngquant;

use Exception\BinaryNotFoundException;
use Exception\IOErrorException;

/**
 * A wrapper for the pngquant utility
 * @link http://pngquant.org/
 *
 * Currently this call in only compatible with POXIS enviroments,
 * no Mi*soft Windows compatibility is intented at all
 */
class Pngquant {

	static private pngquant = "/usr/bin/pngquant";

	private min_quality = null;
	private max_quality = null;
	private path = null;
	private new_path = null;
	private processed = false;
	private blob = false;


	/**
	 * Runs the requires checks for the class to work.
	 * the method first read the <b>pngquant_path</b> ini setting
	 * if the setting is undefined the class will try to <i>guess</i> the
	 * path of the command line utility. Otherwise an exception is raised
	 * 
	 * @return void
	 * @throw Exception\BinaryNotFoundException
	 */
	protected function _doChecks() -> void {
		var ini_setting, output;
		int exitstatus = 0;

		let output = [];

		let ini_setting = ini_get("pngquant_path");

		if ini_setting === false {
			let self::pngquant = exec("command -v pngquant", output, exitstatus);
		}

		if intval(exitstatus) != 0 {
			throw new Exception\BinaryNotFoundException();
		}
	}

	/**
	 * Parses and process the arguments before being passed to the command
	 * 
	 * @return string; $args a string contaning all parameters
	 * @throws Exception\OutOfBoundsException
	 * @throws Exception\RangeException
	 */
	protected function _processArgs() -> string {
		var args;

		let args = "";

		if $this->min_quality != null && $this->max_quality != null {

			if $this->min_quality > 100 {
				throw new \OutOfBoundsException("min quality should be lower than 100");
			}	

			if $this->min_quality < 0 {
				throw new \OutOfBoundsException("min quality should be greater than 0");
			}	

			if $this->max_quality > 100 {
				throw new \OutOfBoundsException("max quality should be lower than 100");
			}	

			if $this->max_quality < 0 {
				throw new \OutOfBoundsException("max quality should be greater than 0");
			}

			if $this->min_quality > $this->max_quality {
				throw new \RangeException("min quality should be lower than max quality");
			}

			let args = sprintf("--quality=%2d-%2d", $this->min_quality, $this->max_quality);
		}

		return args;

	}

	/**
	 * Run the pngquant binary. This method takes care of checking if the file
	 * is readable and spawning a a pngquant process in order to compress the image
	 * 
	 * @return void
	 * @throws Exception\IOErrorException if the source file can't be readed
	 * @throws Exception\PngquantException if the compress process didn't succeed
	 */
	protected function _processFile() -> void {

		// buffer the image
		if $this->processed == false {

			if !is_file($this->path) || !is_readable($this->path) {
				throw new Exception\IOErrorException(sprintf("unable to open '%s' file", $this->path));
			}

			var args, descriptorspec, pipes, status, fd;

			let args = $this->_processArgs();
			let pipes = [];

			let descriptorspec = [
					0 : ["pipe", "r"],
					1 : ["pipe", "w"],
					2 : ["pipe", "w"]
					];

			let fd = proc_open(self::pngquant . " " . args . " - < " . escapeshellarg($this->path), descriptorspec, pipes);

			let $this->blob = stream_get_contents(pipes[1]);
			
			// close all pipes
			fclose(pipes[0]);
			fclose(pipes[1]);
			fclose(pipes[2]);

			let status = proc_get_status(fd);

			proc_close(fd);

			if intval(status["exitcode"]) != 0 {
				throw new Exception\PngquantException(sprintf("non-zero exit status code returned: %d ", status["exitcode"]));
			}

			let $this->processed = true;
		}

	}

	/**
	 * The constructor method
	 */
	public function __construct(string path = null) {

		if path !== null {
			let $this->path = path;
		}

		$this->_doChecks();
	}

	/**
	 * Sets the path of the image to compress
	 * 
	 * @param $path the path of the image to compress
	 * @return void
	 */
	public function setImage(string path) -> void {
		let $this->path = path;
		let $this->processed = false;
	}

	/**
	 * Sets the path of the image to compress
	 * 
	 * @return string the path to the pngquant binary
	 */
	public function pngquantBin() -> string {
		return self::pngquant;
	}

	/**
	 * The public wrapper for the compression process.
	 * 
	 * @param string|void the new file path where the compressed image should be saved
	 * @return void
	 * @throws Exception\IOErrorException if the destination file can't be writen
	 */
	public function compress(string new_path = null) -> void {

		var save;

		$this->_processFile();

		let save = (new_path !== null) ? new_path : $this->path;

		if file_put_contents(save, $this->blob) == 0 {
			throw new Exception\IOErrorException(sprintf("unable to write to '%s'", save));
		}

	}

	/**
	 * Return the blob of the image compressed
	 * 
	 * @return string $blob
	 */
	public function getBlob() -> string {
		$this->_processFile();
		return $this->blob;
	}

	/**
	 * Set the wanted quality for the compression
	 * 
	 * @param $min the mininal required quality
	 * @param $min the maximun required quality
 	 * @return void
	 */
	public function quality(int min, int max) -> void  {
		let $this->min_quality = min;
		let $this->max_quality = max;
	}

}
