#include "dfs_iterator.h"
#include "folder.h"
#include "file.h"

bool isFolder(Node *node)
{
    // printf("test\n");
    Node *temp = dynamic_cast<File *>(node);
    if (temp)
    {
        // printf("true\n");
        return !temp->getClassIterator();
    }
    // printf("false\n");
    return true;
}

DfsIterator::DfsIterator(Node *composite) : _composite(composite)
{
    _temp.clear();
};

void DfsIterator::first()
{
    // composite must be the folder in the first giving on this pattern
    _it = dynamic_cast<Folder *>(_composite)->_files.begin();
};

Node *DfsIterator::currentItem() const
{
    return *_it;
};

// todo recursive method
void DfsIterator::next()
{
    if (!isDone())
    {
        if (isFolder(*_it))
        {
            // printf("test1\n");
            _temp.push_back(_it);
            _it = dynamic_cast<Folder *>(*_it)->_files.begin();
        }
        // identity file iterator => nullptr
        else
        {
            _it++;
            while (_temp.size() > 0 && _it == dynamic_cast<Folder *>(*_temp.back())->_files.end())
            {
                // printf("test2\n");
                // if SubFolder is end, then will back to RootFolder
                printf("Folder end\n");
                _it = _temp.back();
                _temp.pop_back();
                _it++;
            }
        }
    }
    else
    {
        /* jump */
    }
};

bool DfsIterator::isDone() const
{
    return _it == dynamic_cast<Folder *>(_composite)->_files.end();
};



/*   */







