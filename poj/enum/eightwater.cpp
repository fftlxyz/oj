#include <iostream>
#include <queue>

using namespace std;


class Node
{
    public:

        Node(const Node &obj);
        Node();

        int hashCode();
        int& operator[](std::size_t n);

        bool left(Node &node);
        bool right(Node &node);
        bool up(Node &node);
        bool down(Node &node);

        Node& operator=(const Node &obj);
        bool operator==(const Node &rhs);
        bool operator!=(const Node &rhs);
        friend istream &operator>>(istream &is, Node &item);
        friend ostream &operator<<(ostream &os, const Node &item);

    private:
        int state[9];
    public:
        int emptypos;
        string solution;
};

istream &operator>>(istream &is, Node &item);
ostream &operator<<(ostream &os, const Node &item);

//9!
bool vis[362880] = {0};

int main(int argc, const char *argv[])
{
    Node start;
    Node end;

    for(int i =0; i < 9; i++)
        end[i] = i+1;

    cin >> start;

    queue<Node> nodeQueue;

    nodeQueue.push(start);

    string ans = "unsolvable";
    while( !nodeQueue.empty() ) {

        Node head = nodeQueue.front();
        nodeQueue.pop();

        Node tmp;


        if( head.right(tmp) && !vis[ tmp.hashCode()] ) {

            if(tmp == end) {
                ans = tmp.solution;
                break;
            }
            else {
                vis[ tmp.hashCode()] = true;
                nodeQueue.push(tmp);
            }
        }

        if( head.down(tmp) && !vis[ tmp.hashCode()] ) {

            if(tmp == end) {
                ans = tmp.solution;
                break;
            }
            else {
                vis[ tmp.hashCode()] = true;
                nodeQueue.push(tmp);
            }
        }

        if( head.up(tmp) && !vis[ tmp.hashCode()] ) {

            if(tmp == end) {
                ans = tmp.solution;
                break;
            }
            else {
                vis[ tmp.hashCode()] = true;
                nodeQueue.push(tmp);
            }
        }

        if( head.left(tmp) && !vis[ tmp.hashCode()] ) {

            if(tmp == end) {
                ans = tmp.solution;
                break;
            }
            else {
                vis[ tmp.hashCode()] = true;
                nodeQueue.push(tmp);
            }
        }
    }

    cout << ans << endl;

    return 0;
}



istream &operator>>(istream &is, Node &item)
{
    for(int i =0; i < 9; ++i)
    {
        char ch;
        is >> ch;
        if(ch != 'x')
            item.state[i] = (int)(ch - '0');
        else {
            item.emptypos = i;
            item.state[i] = 9;
        }
    }
    return is;
}

ostream &operator<<(ostream &os, const Node &item)
{
    os << item.emptypos << endl;
    for(int i =0; i < 9; ++i)
    {
        if( item.state[i] == 9)
            os << '*' << " ";
        else
            os << (char)('0' + item.state[i]) << " ";

        if( (i + 1) %3 == 0 && i != 8)
            os << endl;
    }
    return os;
}


int Node::hashCode()
{
    static int perm[] = {1,1,2,6,24,120,720,5040,40320};
    int h = 0;

    //找全排列的hash方法
    for(int i =0; i < 9; ++i)
    {
        int count =0;
        for(int j =0 ;j < i; ++j) {
            if( state[i] < state[j])
                ++count;
        }
        h += perm[i] * count;
    }

    return h;
}

bool Node::operator==(const Node &rhs)
{
    for(int i = 0; i < 9; ++i) {
        if( rhs.state[i] != state[i])
            return false;
    }
    return true;
}
bool Node::operator!=(const Node &rhs)
{
    return !(*this == rhs);
}

Node& Node::operator=(const Node &obj)
{
    emptypos = obj.emptypos;
    solution = obj.solution;
    for(int i = 0; i < 9; ++i)
        state[i] = obj.state[i];

    return *this;
}


Node::Node()
{
    // emptypos = -1;
}

Node::Node(const Node &obj)
{
    emptypos = obj.emptypos;

    solution = obj.solution;

    for(int i =0; i < 9; ++i)
        state[i] = obj.state[i];
}

int& Node::operator[](std::size_t n)
{
    return state[n];
}


bool Node::left(Node &node)
{
    bool isok = (emptypos %3 != 0);

    if(isok) {
        node = *this;
        node.state[ emptypos ] = node.state[ emptypos -1 ];
        node.state[ emptypos - 1 ] = 9;
        node.emptypos = emptypos - 1;
        node.solution += 'l';
    }

    return isok;
}

bool Node::right(Node &node)
{
    bool isok = (emptypos %3 != 2);

    if(isok) {
        node = *this;
        node.state[ emptypos ] = node.state[ emptypos + 1 ];
        node.state[ emptypos + 1 ] = 9;
        node.emptypos = emptypos + 1;
        node.solution += 'r';
    }
    return isok;
}

bool Node::up(Node &node)
{

    bool isok = (emptypos / 3 );

    if(isok) {
        node = *this;
        node.state[ emptypos ] = node.state[ emptypos - 3 ];
        node.state[ emptypos - 3 ] = 9;
        node.emptypos = emptypos - 3;
        node.solution += 'u';
    }

    return isok;
}

bool Node::down(Node &node)
{

    bool isok = (emptypos / 3  != 2);

    if(isok) {
        node = *this;
        node.state[ emptypos ] = node.state[ emptypos + 3 ];
        node.state[ emptypos + 3 ] = 9;
        node.emptypos = emptypos + 3;
        node.solution += 'd';
    }

    return isok;
}
