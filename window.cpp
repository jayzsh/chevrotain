#include </usr/lib/x86_64-linux-gnu/glibmm-2.4/include/glibmmconfig.h>
#include </usr/include/glibmm-2.4/glibmm.h>
#include </usr/include/gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

Gtk::Window *sdcvgui_window = nullptr;
Gtk::Button *about_button = nullptr;
Gtk::TextView *search_bar = nullptr;
Gtk::Button *search_button = nullptr;
Gtk::TextView *res_box = nullptr;
Glib::RefPtr<Gtk::TextBuffer> buffer;

std::fstream file;

void on_about_button_clicked ()
{
	exit(0);
}

void on_search_button_clicked ()
{
	std::string res = "";
	char res2[17000];
	auto search_entry = search_bar->get_buffer ();
	std::string search_cmd = search_entry->get_text ();
	system ("mkdir .sdcvgui");
	search_cmd = "echo $(sdcv " + search_cmd + ") >> ./.sdcvgui/.gtk"; 
	char *a = (char*) malloc (search_cmd.size());
	for (int i = 0; i < search_cmd.length(); i++)
		*(a + i) = search_cmd.at(i);
	system (a);
	file.open(".sdcvgui/.gtk", std::ios::in);
	file.getline(res2, 17000);
	buffer->set_text(res2);
	res_box->set_buffer(buffer);
	free(a);
	file.close();
	system("rm ./.sdcvgui/.gtk");
}

int main (int argc, char *argv[])
{
	auto app = Gtk::Application::create (argc, argv, "org.ivorytone.sdcvgui");
	auto builder = Gtk::Builder::create ();

	builder->add_from_file ("sdcv.glade");

	builder->get_widget ("sdcv_window", sdcvgui_window);
	builder->get_widget ("about_button", about_button);
	builder->get_widget ("search_bar", search_bar);
	builder->get_widget ("search_button", search_button);
	builder->get_widget ("result_view", res_box);

	buffer = Gtk::TextBuffer::create();

	about_button->signal_clicked ().connect (sigc::ptr_fun (on_about_button_clicked));
	search_button->signal_clicked ().connect (sigc::ptr_fun (on_search_button_clicked));

	app->run(*sdcvgui_window);
}
