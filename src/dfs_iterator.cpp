#include "dfs_iterator.h"
#include "folder.h"
#include "file.h"

/* dfs_iterator */

bool isFolder(Node *node)
{
    // printf("test\n");
    Node *temp = dynamic_cast<File *>(node);
    if (temp)
    {
        // printf("false\n");
        return !temp->getClassIterator();
    }
    // printf("true\n");
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

/* bfs_iterator */

BfsIterator::BfsIterator(Node *composite) : _composite(composite)
{
    _temp.clear();
    _temp2.clear();
    _i = 0;
    _state = false;
}

void BfsIterator::first()
{
    _it = dynamic_cast<Folder *>(_composite)->_files.begin();
}

Node *BfsIterator::currentItem() const
{
    return *_it;
}

void BfsIterator::next()
{
    if (isFolder(*_it))
    {
        printf("folder\n");
        _temp2.push_back(_it);
    }
    printf("++\n");
    _it++;

    if (_it == dynamic_cast<Folder *>(_composite)->_files.end())
    {
        printf("done1\n");
        _temp.clear();
        _temp = _temp2;
        _temp2.clear();
        _i = 0;

        _it = dynamic_cast<Folder *>(*_temp[_i])->_files.begin();
        _i++;
    }
    else if (_temp.size() > 0 && _it == dynamic_cast<Folder *>(*_temp[_i - 1])->_files.end())
    {
        printf("subdone\n");
        if (_i == _temp.size())
        {
            printf("done2\n");
            _temp.clear();
            _temp = _temp2;
            _temp2.clear();
            _i = 0;

            if (_temp.size() == 0)
            {
                printf("close\n");
                _state = true;
                return;
            }
            else
            {
                _it = dynamic_cast<Folder *>(*_temp[_i])->_files.begin();
                _i++;
            }
        }
        else
        {
            printf("switch\n");
            _it = dynamic_cast<Folder *>(*_temp[_i])->_files.begin();
            _i++;
        }
    }
}

//TODO the end-point is on the last step
bool BfsIterator::isDone() const
{
    return _state;
}
