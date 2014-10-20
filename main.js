
// load the native module
var aw = require("./src");

// create an appware application
var app = new aw.App();
// app.stop()

// create a form
// var form = new aw.Form({
// 	'origin' : new aw.Point(1000,0),
// 	'size' : new aw.Size(300,300),
// 	'backgroundColor' : new aw.Color(0,0,0,1)
// });

var obj = new aw.Test("test");

obj.test()



// form.close(function(){})
// form.minimize(function(){});
// form.maximize(function(){});
// form.fullscreen(function(){});
// form.focus(function(){});
// form.update(function(){});
// form.zoom(function(){});

// form.on("move",function(){
// 	console.log('callback called!')
// });




app.exec();
