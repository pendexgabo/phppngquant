namespace Pngquant\Exception;


class PngquantException extends \Exception {

	public function __construct(string message = null) {
		let $this->message = message;
	}

	public function __toString () -> string {
		return $this->message;
	}

}