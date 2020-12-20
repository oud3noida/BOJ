#include <iostream>
#include <list>
#include <cassert>

using namespace std;

list<char> editor;
list<char>::iterator editor_cursor;

int main()
{
    string s;
    cin >> s;

    for (char c : s) editor.push_back(c);
    editor_cursor = editor.end();

    int n;
    cin >> n;
    
    char command;
    for (int i=0; i<n; ++i) {
        cin >> command;
        switch (command) {
        case 'L':
            if (editor_cursor != editor.begin())
                --editor_cursor;
            break;
        case 'D':
            if (editor_cursor != editor.end())
                ++editor_cursor;
            break;
        case 'B':
            if (editor_cursor != editor.begin())
                editor_cursor = editor.erase(--editor_cursor);
            break;
        case 'P':
            cin >> command;
            editor.insert(editor_cursor, command);
            break;
        default:
            assert(false);
    	}
    }

    for (auto it = editor.begin(); it != editor.end(); ++it) {
        cout << *it;
    }

    return 0;
}