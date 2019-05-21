include("rvi/font.lua");
include("rvi/color.lua");
include("rvi/text_format.lua");

function nu_dialog(id, nxt, text)
    dialog.declare_page(id);
    dialog.set_page_text(id, text);
    dialog.set_next_page(id, nxt);
end

r_set_color("orange");

nu_dialog("001", "002", "Hi there friend");
nu_dialog("002", "003", "How are ya doing?");
nu_dialog("003", "004", "I've been looking into the elevator malfunction.");
nu_dialog("004", "005", "Seems to be working fine now.");
nu_dialog("005", "006", "Ha...");
nu_dialog("006", "007", "...Well");
nu_dialog("007", "008", "Regardless, have a nice evening.");

dialog.declare_page("008");
dialog.goto_page("001");
dialog.refresh();
