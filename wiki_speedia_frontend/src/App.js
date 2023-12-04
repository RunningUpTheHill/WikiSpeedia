import React from 'react';
import './App.css';
import GraphView from './components/graph';

function App() {
    return (
        <div className="App">
            <div className="sidebar">
                {/* Sidebar content */}
                {/* You can add navigation links, content, or any other elements */}
            </div>
            <div className="content">
                <GraphView />
            </div>
        </div>
    );
}

export default App;
