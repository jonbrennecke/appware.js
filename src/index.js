(function ( mod ) {

	// load the native module
	module.exports = mod(require("./build/Release/test"));

})(function ( aw ) {

	aw.meta = { name : "AppWare", version : "0.0.1" };

	/**
	 * Point ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	aw.Point = function ( x, y ) {
		this.x = x;
		this.y = y;
	}
	aw.Point.prototype = {};

	/**
	 * Size ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	aw.Size = function ( w, h ) {
		this.width = w;
		this.height = h;
	}
	aw.Size.prototype = {};

	/**
	 * Rectangle ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	aw.Rect = function( o, s ) {
		this.origin = o;
		this.size = s;
	}
	aw.Rect.prototype = {};




	return aw;
});