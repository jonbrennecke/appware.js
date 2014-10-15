{
	"targets" : [
		{
			"target_name" : "test",
			"sources" : ["test/test-objc.mm", "test/test.cpp"],
			"conditions" : [
				[ "OS == 'mac'", {
					"xcode_settings": {
		                "OTHER_CPLUSPLUSFLAGS" : [ "-Wall","-std=c++11"],
		                "MACOSX_DEPLOYMENT_TARGET": "10.7",
		                "CLANG_CXX_LIBRARY": "libc++"
		            },
		            "link_settings": {
		            	"libraries": [
		            		"-lobjc",
		            		"-framework",
		            		"Cocoa" 
		            	]
		            }
				}]
			]
		}
	]
}