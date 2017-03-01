#include "Parser.h"

Parser::Parser(bool other_gather_urls)
	: output(nullptr), gather_urls(other_gather_urls)
{
};

Parser::~Parser()
{
	// Get rid of the tree and reset unique ptr
	gumbo_destroy_output(&kGumboDefaultOptions, output);
	output = nullptr;
}


// Attempt to convert the stream to a tree. Does it work?
// dont think the output.errors are implemented so..
bool Parser::load_stream(std::stringstream& stream)
{
	output = gumbo_parse(stream.str().c_str());
	if (output == nullptr || output->root == nullptr)
	{
		return false;
	}
	return true;
};

// Travel from node to node and determine whether they contain text to split and store
// or an element with possible links and children
void Parser::traverse_tree()
{
	std::stack<GumboNode*> stack;
	stack.push(output->root);
	while(!stack.empty())
	{
		GumboNode* current_node = stack.top();
		stack.pop();
		if (current_node->type == GUMBO_NODE_ELEMENT)
		{
			if (gather_urls)
			{
				search_for_link(current_node);
			}
			// Add children to stack
			GumboVector* children = &current_node->v.element.children;
			for (uint32_t i = 0; i < children->length; i++)
			{
				stack.push(static_cast<GumboNode*>(children->data[i])); // CAST IS IMPORTANT, DATA IS VOID*
			}
		}
		else
		{
			if (current_node->type == GUMBO_NODE_TEXT)
			{
				std::stringstream text{current_node->v.text.text};
				std::copy(std::istream_iterator<std::string>(text),
					  std::istream_iterator<std::string>(), std::back_inserter(data_gathered));
			}
		}
	}
}

void Parser::search_for_link(GumboNode* node)
{
	if (node->v.element.tag == GUMBO_TAG_A)
	{
		GumboAttribute* link = gumbo_get_attribute(&node->v.element.attributes, "href");
		if (link)
		{
			urls_gathered.insert(link->value);
		}
	}
}



// Dump data to the ConnectionMaster
void Parser::return_data(std::vector<std::string>* url_pool, std::set<std::string>* data_pool)
{
	std::copy(urls_gathered.begin(), urls_gathered.end(), std::back_inserter((*url_pool)));
	std::copy(data_gathered.begin(), data_gathered.end(), std::inserter(*data_pool, data_pool->end()));
}
