// Webgraph.cpp
// Author: Jinwei Shen
//
// Implementation of Webgraph class functions

#include "Node.h"
#include "Webgraph.h"
#include <queue>

typedef unsigned int uint;

using namespace std;

const vector<Node>& Webgraph::getAllNodes() const {
    return all_nodes;
}

bool Webgraph::hasLink(const string &url_) const {
    for (uint i=0; i<all_nodes.size(); ++i) {
        if (all_nodes[i].getUrl() == url_) { return true; }
    }
    return false;
}

// Assume the node with the provided url exists
const Node& Webgraph::getNodeFromLink(const std::string &url_) const {
    uint i = 0;
    for (; i<all_nodes.size(); ++i) {
        if (all_nodes[i].getUrl() == url_) { break; }
    }
    return all_nodes[i];
}

// Assume the provided node exists
const std::vector<Node>& Webgraph::getIncomingNodes(const Node &n) const {
    return n.getParents();
}

// Assume the provided node exists
const std::vector<Node>& Webgraph::getOutgoingNodes(const Node &n) const {
    return n.getChildren();
}

const std::map< std::string, float>& getAllRanks() const{
    std::map< std::string, float > all_ranks;
    for (int i=0; i<all_links.size(); ++i){
        all_ranks[all_links[i].getUrl()] = all_links[i].getRank();
    }
    return all_ranks;
}

bool Webgraph::addLink(const string &url_) {
    if (hasLink(url_)) { return false; }
    Node n(url_);
    all_nodes.push_back(n);
    adj_matrix[n] = vector<Node>();
    return true;
}

bool Webgraph::addConnection(const std::string &from_url,
                                const std::string &to_url) {
    if (hasLink(from_url) == false) {
        addLink(from_url);
    }
    if (hasLink(to_url) == false) {
        addLink(to_url);
    }
    // update Node info
    Node n_from = getNodeFromLink(from_url);
    Node n_to = getNodeFromLink(to_url);
    bool added = n_from.addChild(n_to);
    n_to.addParent(n_from);
    // update adj matrix
    if (added == false) { return false; }
    adj_matrix[n_from].push_back(n_to);
    return true;
}


/inital the rank update, assume url exists
void Webgraph::updateRank(const string &url_) {
    //inital the queue and start the iterative update
    queue<Node> work_queue;
    Node start = getNode(url_);
    work_queue.push(start);
    updateHelper(work_queue);
    return;
}

//actual rank update function, iterative update the 
//rank of the nodes until the queue is empty
void Webgraph::updateHelper(queue<Node> work_queue){
    //finish condition
    if (work_queue.empty()){
        return;
    }

    //update the rank of the node that is on the top
    //of the queue
    Node n_current = work_queue.pop()
    //calculate new rank based on incoming nodes
    vector<Node> parent = getIncomingNodes(n_current);
    float new_rank = 0;
    for (int i=0; i<parent.size(); ++i){
        Node n_from = from_list[i];
        float from_rank = n_from.getRank();
        int outgoing_number = getOutgoingNodes(n_from).size();
        new_rank += from_rank/outgoing_number;
    }
    new_rank = 0.15 + 0.85*new_rank;
    old_rank = n_current.getRank();
    //update the rank
    n_current.updateRank(new_rank);

    //check converge, threshold current set to 0.1% 
    if (abs(new_rank - old_rank)/old_rank < 0.001){
        //converged, current node's children would not add to queue
        updateHelper(work_queue);
    }
    else{
        //not converged, all current node's children to queue
        vector<Node> children = getOutgoingNodes(n_current);
        for (int i=0; i<children.size(); ++i) {
            work_queue.push(children[i])
        }
        updateHelper(work_queue);
    }
    return;
}