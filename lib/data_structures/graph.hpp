#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <memory>
#include <string>

template <typename T>
class Graph
{

public:
    struct Edge
    {
        T src;
        T dest;
        T weight;

        friend std::ostream& operator<<(std::ostream& os_, const Edge& edge_)
        {
            os_ << edge_.src << " --" << edge_.weight << "-- " << edge_.dest << " ";
            return os_;
        }
    };

    struct Path
    {
        T weight;
        std::vector<Edge> edgeVect;

        friend std::ostream& operator<<(std::ostream& os_, const Path& path_)
        {
            std::copy(path_.edgeVect.begin(), path_.edgeVect.end(), std::ostream_iterator<Edge>(os_, ""));
            os_ << "(" << path_.weight << ")";
            return os_;
        }
    };

    Graph(const std::vector<Edge>& edgesVect_)
    {
        for (const Edge& edge : edgesVect_)
        {
            auto getNode = [&](const T& t_)
            {
                auto [it, inserted] = _nodePtrMap.try_emplace(t_, nullptr);
                if (inserted)
                {
                    it->second = std::make_shared<Node>(t_);
                }
                return it->second;
            };

            const NodePtr& srcNodePtr {getNode(edge.src)};
            const NodePtr& destNodePtr {getNode(edge.dest)};

            EdgeImpl edgeImpl(edge.weight, srcNodePtr, destNodePtr);

            srcNodePtr->destEdgeImplVect.emplace_back(edgeImpl);
            destNodePtr->srcEdgeImplVect.emplace_back(edgeImpl);
            _pathImplMap.emplace(std::make_pair(edge.src, edge.dest), PathImpl({edgeImpl}));
        }
    }

    std::vector<Path> getAllPathBFS(const T& src_, const T& dest_) const
    {
        std::vector<Path> pathVect;
        auto srcIt {_nodePtrMap.find(src_)};
        auto destIt {_nodePtrMap.find(dest_)};
        if (srcIt != _nodePtrMap.end() && destIt != _nodePtrMap.end())
        {
            auto pathImplVect {getAllPathBFS(srcIt->second, destIt->second)};
            std::sort(std::begin(pathImplVect), std::end(pathImplVect));
            std::for_each(std::begin(pathImplVect), std::end(pathImplVect), [&](const auto& p_){ pathVect.emplace_back(p_.toPath()); });
        }
        return pathVect;
    }

    std::vector<Path> getAllPathDFS(const T& src_, const T& dest_) const
    {
        std::vector<Path> pathVect;
        auto srcIt {_nodePtrMap.find(src_)};
        auto destIt {_nodePtrMap.find(dest_)};
        if (srcIt != _nodePtrMap.end() && destIt != _nodePtrMap.end())
        {
            auto pathImplVect {getAllPathDFS(srcIt->second, destIt->second)};
            std::sort(std::begin(pathImplVect), std::end(pathImplVect));
            std::for_each(std::begin(pathImplVect), std::end(pathImplVect), [&](const auto& p_){ pathVect.emplace_back(p_.toPath()); });
        }
        return pathVect;
    }

private:
    struct Node;
    using NodePtr = std::shared_ptr<Node>;

    struct EdgeImpl
    {
        EdgeImpl(const T& weight_, const NodePtr& srcNode_, const NodePtr& destNode_) : weight(weight_), srcNodePtr(srcNode_), destNodePtr(destNode_) {}

        T weight;
        NodePtr srcNodePtr;
        NodePtr destNodePtr;

        Edge toEdge() const
        {
            return {srcNodePtr->data, destNodePtr->data, weight};
        }
    };

    struct Node
    {
        Node() = default;
        Node(const T& data_) : data(data_) {}

        T data;
        std::vector<EdgeImpl> srcEdgeImplVect;
        std::vector<EdgeImpl> destEdgeImplVect;

        friend std::ostream& operator<<(std::ostream& os_, const Node& node_)
        {
            os_ << "[" << node_.data << "] [ ";
            std::for_each(std::begin(node_.srcEdgeImplVect), std::end(node_.srcEdgeImplVect), [](const auto& eI_) { std::cout << eI_.toEdge(); });
            std::cout << "] [ ";
            std::for_each(std::begin(node_.destEdgeImplVect), std::end(node_.destEdgeImplVect), [](const auto& eI_) { std::cout << eI_.toEdge(); });
            std::cout << "]";
            return os_;
        }
    };

    struct PathImpl
    {
        PathImpl() : weight(T{}) {}

        PathImpl(const std::vector<EdgeImpl>& edgeImplVect_) : edgeImplVect(edgeImplVect_)
        {
            updateWeight();
        }

        void emplace_back(const EdgeImpl& edgeImpl_)
        {
            edgeImplVect.emplace_back(edgeImpl_);
            updateWeight();
        }

        void emplace_back(const PathImpl& path_)
        {
            edgeImplVect.insert(std::end(edgeImplVect), std::begin(path_.edgeImplVect), std::end(path_.edgeImplVect));
            updateWeight();
        }

        bool hasLoop() const
        {
            if (edgeImplVect.empty())
            {
                return false;
            }

            std::set<NodePtr> nodePtrSet {edgeImplVect[0].srcNodePtr};

            for (const EdgeImpl& edgeImpl : edgeImplVect)
            {
                const NodePtr nodePtr {edgeImpl.destNodePtr};
                if (nodePtrSet.find(nodePtr) != nodePtrSet.end())
                {
                    return true;
                }
                nodePtrSet.emplace(nodePtr);
            }

            return false;
        }

        bool isValid() const
        {
            return !edgeImplVect.empty();
        }

        Path toPath() const
        {
            std::vector<Edge> edgeVect;
            std::for_each(edgeImplVect.cbegin(), edgeImplVect.cend(), [&](const auto& e_){ edgeVect.emplace_back(e_.toEdge()); });
            return {weight, edgeVect};
        }

        bool operator<(const PathImpl& path_) const
        {
            return (weight < path_.weight) ||
                   (weight == path_.weight && edgeImplVect.size() < path_.edgeImplVect.size());
        }

        T weight;

    private:
        void updateWeight()
        {
            weight = T{};
            for (const EdgeImpl& edgeImpl : edgeImplVect)
            {
                weight += edgeImpl.weight;
            }
        }

        std::vector<EdgeImpl> edgeImplVect;
    };

    std::vector<PathImpl> getAllPathBFS(NodePtr srcNode_, NodePtr destNode_, const PathImpl& inPath_=PathImpl()) const
    {
        PathImpl inPath {inPath_.isValid() ? inPath_ : PathImpl()}; // eliminate root

        std::vector<PathImpl> pathImplVect;
        for (const EdgeImpl& edgeImpl : srcNode_->destEdgeImplVect)
        {
            PathImpl pathImpl = inPath;
            pathImpl.emplace_back(edgeImpl);
            if (!pathImpl.hasLoop())
            {
                NodePtr destNodePtr {edgeImpl.destNodePtr};
                if (destNodePtr == destNode_)
                {
                    pathImplVect.emplace_back(pathImpl);
                }
                else
                {
                    std::vector<PathImpl> pathVectRhs = getAllPathBFS(destNodePtr, destNode_, pathImpl);
                    if (!pathVectRhs.empty())
                    {
                        pathImplVect.insert(std::end(pathImplVect), std::begin(pathVectRhs), std::end(pathVectRhs));
                    }
                }
            }
        }
        return pathImplVect;
    }

    std::vector<PathImpl> getAllPathDFS(NodePtr srcNode_, NodePtr destNode_, const PathImpl& inPath_=PathImpl()) const
    {
        std::vector<PathImpl> pathImplVect;

        std::queue<std::pair<NodePtr, PathImpl>> nodePtrQueue;
        nodePtrQueue.emplace(std::make_pair(srcNode_, PathImpl()));

        while (!nodePtrQueue.empty())
        {
            auto nodePtrPathPair {nodePtrQueue.front()};
            nodePtrQueue.pop();

            NodePtr nodePtr = nodePtrPathPair.first;
            PathImpl inPath = nodePtrPathPair.second;

            for (const EdgeImpl& edgeImpl : nodePtr->destEdgeImplVect)
            {
                PathImpl pathImpl = inPath;
                pathImpl.emplace_back(edgeImpl);
                if (!pathImpl.hasLoop())
                {
                    NodePtr destNodePtr {edgeImpl.destNodePtr};
                    if (destNodePtr == destNode_)
                    {
                        pathImplVect.emplace_back(pathImpl);
                    }
                    else
                    {
                        nodePtrQueue.emplace(std::make_pair(destNodePtr, pathImpl));
                    }
                }
            }
        }

        return pathImplVect;
    }

    std::map<T, NodePtr> _nodePtrMap;
    mutable std::map<std::pair<T, T>, PathImpl> _pathImplMap; // gets updated when finding new path

public:
    friend std::ostream& operator<<(std::ostream& os_, const Graph& graph_)
    {
        std::for_each(graph_._nodePtrMap.begin(), graph_._nodePtrMap.end(), [](const auto& p_) { std::cout << *p_.second << "\n"; });
        return os_;
    }
};
