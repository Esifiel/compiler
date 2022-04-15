#! /usr/bin/python3
# -*- coding: utf-8 -*-

from graphviz import Digraph
from graphviz import Source
import os, json

os.chdir(os.path.dirname(__file__))

dot = Digraph(
    name="AST",
    comment="Visualization of the Abstract Syntax Tree",
    filename="ast",
    directory="../tmp",
    format="png",
    engine="dot",
    encoding="utf8",
)

nodes = []

def json2dot(parent, key, vlist):
    global dot
    
    label = key
    if label in nodes:
        label += len(nodes)
    nodes.append(label)
    dot.node(label, key)
    
    if parent != None:
        dot.edge(parent, label)
    
    for dic in vlist:
        if isinstance(dic, dict):
            child = list(dic.keys())[0]
            vlist = dic[child]
            json2dot(label, child, vlist)
        elif isinstance(dic, str):
            name = dic
            if name in nodes:
                name += str(len(nodes))
            dot.edge(label, name)
        else:
            raise Exception("Cannot confirm type of %s" % str(dic))
                    
ast = json.loads(open("../tmp/ast.json", "r").read())
root = "Program"
json2dot(None, root, ast[root])
dot.view()