namespace Pngquant\Exception;


class IOErrorException extends PngquantException {

	public function __construct(string message) {
		let $this->message = message;
	}

	public function __toString () -> string {
		return $this->message;
	}

}