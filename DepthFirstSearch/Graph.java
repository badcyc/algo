package dataStructure.DepthFirstSearch;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * @program: algo
 * @description: 无向图的深度优先搜索DFS和图的广度优先搜索
 * @author: Yichao Chen
 * @create: 2018-10-31 21:13
 **/
class Node {
    int value;

    Node(int value) {
        this.value = value;
    }
}

class Vertex {
    Node first;
    Node second;

    Vertex(Node first, Node second) {
        this.first = first;
        this.second = second;
    }
}

class VertexType {
    private HashMap<Integer, Boolean> visitedList = new HashMap<>();
    private List<Node> nodeList = new ArrayList<>();
    private List<Vertex> vertexList = new ArrayList<>();

    private void setNodeList(List<Node> nodeList) {
        this.nodeList = nodeList;
    }

    private void setVertexList(List<Vertex> vertexList) {
        this.vertexList = vertexList;
    }

    public void DFS() {
        for (Node node :
                nodeList) {
            if (!visitedList.containsKey(node.value)) {
                dfs(node);
            }
        }
    }

    private void dfs(Node first) {
        visitedList.put(first.value, true);
        System.out.println(first.value);
        for (Vertex v :
                vertexList) {
            if (v.first.equals(first) || v.second.equals(first)) {
                if (v.first.equals(first)) {
                    if (!visitedList.containsKey(v.second.value)) {
//                        System.out.println(v.second.value);
                        dfs(v.second);
//                        System.out.println(v.second.value);
                    }
                } else {
                    if (!visitedList.containsKey(v.first.value)) {
//                        System.out.println(v.first.value);
                        dfs(v.first);
                    }
                }
            }
        }
    }

    private HashMap<Integer, Boolean> bfsVisitedList = new HashMap<>();

    public void BFS() {
        for (Node node :
                nodeList) {
            if (!bfsVisitedList.containsKey(node.value)) {
                bfs(node);
            }
        }
    }

    private void bfs(Node node) {
        System.out.println(node.value);
        for (Vertex v :
                vertexList) {
            if (v.first.equals(node)) {
                if (!bfsVisitedList.containsKey(v.second.value)) {
                    bfsVisitedList.put(v.second.value, true);
                    System.out.println(v.second.value);
                }
                continue;
            }
            if (v.second.equals(node)) {
                if (!bfsVisitedList.containsKey(v.first.value)) {
                    bfsVisitedList.put(v.first.value, true);
                    System.out.println(v.first.value);
                }
            }
        }
        bfsVisitedList.put(node.value, true);
    }

    public static void main(String[] args) {
        List<Node> nodeList = new ArrayList<>();
        Node node = new Node(1);
        Node node2 = new Node(2);
        Node node3 = new Node(3);
        Node node4 = new Node(4);
        Node node5 = new Node(5);
        Node node6 = new Node(6);
        nodeList.add(node);
        nodeList.add(node2);
        nodeList.add(node3);
        nodeList.add(node4);
        nodeList.add(node5);
        nodeList.add(node6);
        Vertex vertex = new Vertex(node, node4);
        Vertex vertex2 = new Vertex(node, node3);
        Vertex vertex3 = new Vertex(node, node2);
        Vertex vertex4 = new Vertex(node4, node5);
        Vertex vertex5 = new Vertex(node4, node6);
        List<Vertex> verticeList = new ArrayList<>();
        verticeList.add(vertex);
        verticeList.add(vertex2);
        verticeList.add(vertex3);
        verticeList.add(vertex4);
        verticeList.add(vertex5);
        VertexType vertexType = new VertexType();
        vertexType.setNodeList(nodeList);
        vertexType.setVertexList(verticeList);
        System.out.println("DFS:");
        vertexType.DFS();
        System.out.println("BFS:");
        vertexType.BFS();
    }
}
