import React from 'react'
import Graph from 'react-vis-network-graph'

export default function GraphView() {
    const graph = {
        nodes: [
            {id: 1, label: "Node 1", title: "node 1 tooltip text"},
            {id: 2, label: "Node 2", title: "node 2 tooltip text"},
            {id: 3, label: "Node 3", title: "node 3 tooltip text"},
            {id: 5, label: "Node 5", title: "node 5 tooltip text"},
            {id: 6, label: "Node 6", title: "node 6 tooltip text"},
            {id: 7, label: "Node 7", title: "node 7 tooltip text"},
            {id: 8, label: "Node 8", title: "node 8 tooltip text"}
        ],
        edges: [
            {from: 1, to: 1},
            {from: 1, to: 7},
            {from: 1, to: 3},
            {from: 6, to: 5},
            {from: 6, to: 2},
            {from: 7, to: 2},
            {from: 6, to: 7},
            {from: 6, to: 8},
            {from: 7, to: 8},
            {from: 8, to: 2},
            {from: 3, to: 7},
        ]
    }

    var options = {
        physics: {
            enabled: false
        },
        interaction: {
            navigationButtons: true
        },
        nodes: {
            borderWidth: 4,
            size: 45,
            color: {
                border: "black",
                background: "white"
            },
            font: {color: "purple"}
        },
        edges: {
            color: "white"
        },
        shadow: true,
        smooth: true,
        height: "900px"
    }
    return (
        <div className='container'>
            <Graph
                graph={graph}
                options={options}
            />
        </div>
    )
}