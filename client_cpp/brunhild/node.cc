#include "node.hh"
#include "util.hh"

unsigned long long id_counter = 0;

namespace brunhild {

std::string new_id()
{
    std::ostringstream s;
    s << "bh-" << id_counter++;
    return s.str();
}

std::string Node::html() const
{
    std::ostringstream s;
    write_html(s);
    return s.str();
}

void Node::write_html(std::ostringstream& s) const
{
    s << '<' << tag;
    for (auto & [ key, val ] : attrs) {
        s << ' ' << key;
        if (val != "") {
            s << "=\"" << val << '"';
        }
    }
    s << '>';

    // These should be left empty and unterminated
    if (tag == "br" || tag == "wbr") {
        return;
    }

    if (inner_html) {
        s << *inner_html;
    } else {
        for (auto& ch : children) {
            ch.write_html(s);
        }
    }

    s << "</" << tag << '>';
}

void Node::stringify_subtree()
{
    std::ostringstream s;
    for (auto& ch : children) {
        ch.write_html(s);
    }
    inner_html = s.str();
    children.clear();
}

void Node::clear()
{
    tag.clear();
    attrs.clear();
    children.clear();
    inner_html = std::nullopt;
}
}
