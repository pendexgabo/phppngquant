namespace Pngquant;

use Exception\BinaryNotFoundException;
use Exception\IOErrorException;

/**
 * A wrapper for the pngquant command line utility
 * @link http://pngquant.org/
 *
 * Currently this class in only compatible with POSIX enviroments,
 * no Mi*soft compatibility is intented at all
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
	 * Returns the path to the pngquant binary
	 * 
	 * @return string the path to the pngquant binary
	 */
	public static function pngquantBin() -> string {
		return self::pngquant;
	}

	/**
	 * Runs the required checks for the class to work.
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
	 * Opens and reads the source stream.
	 * 
	 * @return string; (blob) the content of the stream
	 * @throws Exception\IOErrorException if the source stream can't be opened or readed
	 */
	protected function _readSourceFile() -> string {

		var blob;

		if stream_is_local($this->path) && (!is_file($this->path) || !is_readable($this->path)) {
			throw new Exception\IOErrorException(sprintf("unable to open '%s' file", $this->path));
		}

		let blob = file_get_contents($this->path);

		if blob === false {
			throw new Exception\IOErrorException(sprintf("unable to read '%s' file", $this->path));
		}

		return blob;

	}

	/**
	 * Run the pngquant binary. This method takes care of spawning a
	 * pngquant process in order to compress the image.
	 * The pngquant command line will take the source image from <i>stdin</i>
	 * and return the result to <i>stdout</i>
	 * In order to see the result of the operation we read the value
	 * of the exit code.
	 * 
	 * @return void
	 * @throws Exception\IOErrorException if the source file can't be readed
	 * @throws Exception\PngquantException if the compress process didn't succeed
	 */
	protected function _processFile() -> void {

		// buffer the image
		if $this->processed == false {

			var args, descriptorspec, pipes, status, fd, source;

			let args = $this->_processArgs();
			let pipes = [];

			let descriptorspec = [
					0 : ["pipe", "r"],
					1 : ["pipe", "w"],
					2 : ["pipe", "w"]
					];

			let source = $this->_readSourceFile();

			let fd = proc_open(self::pngquant . " " . args . " -", descriptorspec, pipes);

			fwrite($pipes[0], source); // write the

			let source = null;

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
	 *
	 * @return void
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
	 * @param $path; the path of the image to compress
	 * @return void
	 */
	public function setImage(string path) -> void {
		let $this->processed = false;
		let $this->path = path;
	}

	/**
	 * The public wrapper for the compression process.
	 * If you $new_path is not set the original path is used to save
	 * the compressded file.
	 * 
	 * @param string|void the new path where the compressed image should be saved
	 * @return void
	 * @throws Exception\IOErrorException if the destination file can't be writen
	 */
	public function compress(string new_path = null) -> void {

		var save, retval;

		$this->_processFile();

		let save = (new_path !== null) ? new_path : $this->path;

		let retval = file_put_contents(save, $this->blob);

		if retval == 0 || retval === false {
			throw new Exception\IOErrorException(sprintf("unable to write to '%s'", save));
		}

	}

	/**
	 * Return the blob of the compressed image
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
