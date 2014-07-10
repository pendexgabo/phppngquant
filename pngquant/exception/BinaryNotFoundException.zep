namespace Pngquant\Exception;


class BinaryNotFoundException extends PngquantException {

	public function __toString () -> string {
		return "pngquant binary not found";
	}

}