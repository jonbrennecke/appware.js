__Object__

```C++
aw::Object()
```

__Exporter__
```C++
CSSExport& exportToCSS()
JavaExport& exportToJava()
ObjCExport& exportToObjC()
JavascriptExport& exportToJavascript()
HTMLExport& exportToHTML()
```






__Layout__
base class for layouts
- inheriting classes:
	- ContentPage
	- MasterDetailPage
	- NavigationPage
	- TabbedPage
	- CarouselPage
	- StackLayout
	- AbsoluteLayout
	- RelativeLayout
	- GridLayout
	- ContentView
	- ScrollView
	- Frame

__Rect__
```C++
aw::Rect()
aw::Rect(x,y,w,h)
```

__Form__
```C++
aw::Form()
aw::Form(aw::Rect rect)
```

margin
left
top
origin
position

closed
width
height
fullScreen
scrollbars
scrollX
scrollY
scrollMaxX
scrollMaxY




aw::FormViewModel
aw:Form form_

aw::Application();
void exec()



```javascript

var aw = require('AppWare');

var app = new aw.Application();
app.exec();

var rect = new aw.Rect(0,0,100,100);
var window = new aw.Form(rect);

app.add(window);

```






