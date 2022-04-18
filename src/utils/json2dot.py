#! /usr/bin/python3
# -*- coding: utf-8 -*-

from graphviz import Digraph
import os, json, sys

nodes = []

def json2dot(parent, key, vlist):
    global dot
    
    label = key
    if label in nodes:
        label += str(len(nodes))
    nodes.append(label)
    dot.node(label, key)
    
    if parent != None:
        dot.edge(parent, label)
    
    for dic in vlist:
        if isinstance(dic, dict):
            child = list(dic.keys())[0]
            vlist = dic[child]
            json2dot(label, child, vlist)
        else:
            name = str(dic)
            sub_label = name
            if sub_label in nodes:
                sub_label += str(len(nodes))
            nodes.append(sub_label)
            dot.node(sub_label, name)
            dot.edge(label, sub_label)

if len(sys.argv) <= 1:
    print("Usage: python3 json2dot.py <json_path>")
    exit(1)
    
ast = json.loads(open(sys.argv[1], "r").read())
root = "Program"
dot = Digraph(
    name="AST",
    comment="Visualization of the Abstract Syntax Tree",
    filename="ast.dot",
    directory=os.getcwd() + "/tmp",
    format="png",
    engine="dot",
)
dot.graph_attr['rankdir'] = 'LR'

json2dot(None, root, ast[root])
dot.view()