#ifndef __APP_H__
#define __APP_H__

namespace aw
{
	// class Impl
	// {
	// public:
	// 	Impl();
	// 	~Impl();
	// };

	/**
	 *
	 * App ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * class definition for the main application instance
	 *
	 */	
	class App
	{
	public:
		App();
		~App();
		void exec();
	private:
		void* self_;
	};

	/**
	 *
	 * Form ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * represents a window or dialog box that makes up an application's user interface
	 *
	 */
	class Form
	{
	public:
		Form();
		~Form();
	private:
		void* self_;
	};

}

#endif