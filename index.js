(function( mod ){
	module.exports = mod(
		require( __dirname + '/build/Release/appware'),
		require('Q'));
})(function ( Native, Q ) {

	"use strict";

	var awr = { "meta" : "AppWare version 0.0.1" };

	// native objects
	awr.App = Native.App;
	awr.Form = Native.Form;

	/**
	 *
	 * TODO wrap App.__exec__() in an async call
	 *
	 */
	awr.App.prototype.exec = function() {
		this.__exec__();
	}

	/**
	 * Point ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	awr.Point = function ( x, y ) {
		this.x = x;
		this.y = y;
	}
	awr.Point.prototype = {};

	/**
	 * Size ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	awr.Size = function ( w, h ) {
		this.width = w;
		this.height = h;
	}
	awr.Size.prototype = {};

	/**
	 * Rectangle ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 */
	awr.Rect = function( o, s ) {
		this.origin = o;
		this.size = s;
	}
	awr.Rect.prototype = {};

	return awr;
});