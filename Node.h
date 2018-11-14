// Node.h
// Author: Jinwei Shen
//
// Header file for the Node class

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
private:
    std::string url;
    float rank;
    std::string timestamp;
    std::vector<Node> children;  // outgoing connections
    std::vector<Node> parents;   // incoming connections
public:
    // Constructor
    Node(const std::string &url_);
    // Accessor
    const std::string& getUrl() const;
    float getRank() const;
    const std::string& getTimestamp() const;
    const std::vector<Node>& getChildren() const;
    const std::vector<Node>& getParents() const;
    bool hasChild(const Node &child_) const;
    bool hasParent(const Node &parent_) const;

    // Modifier
    bool addChild(const Node &child_);
    bool addParent(const Node &parent_);
    void updateRank(const int rank_);
    void updateTimestamp(const std::string &timestamp_);
    // Operator
    bool operator<(const Node &n) const;
    bool operator==(const Node &n) const;
};
#endif
