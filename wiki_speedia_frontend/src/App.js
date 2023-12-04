// app.js
import React, { useState } from 'react';
import './App.css';
import GraphView from './components/graph';

function App() {
    const [firstCategory, setFirstCategory] = useState('');
    const [firstLink, setFirstLink] = useState('');
    const [secondCategory, setSecondCategory] = useState('');
    const [secondLink, setSecondLink] = useState('');
    const [selectedAlgorithm, setSelectedAlgorithm] = useState('');
    const [timeTaken, setTimeTaken] = useState(0);

    const handleFirstCategoryChange = (event) => {
        setFirstCategory(event.target.value);
        setFirstLink('');
    };

    const handleSecondCategoryChange = (event) => {
        setSecondCategory(event.target.value);
        setSecondLink('');
    };

    const handleGeneratePathClick = () => {

    };

    return (
        <div className="App">
            <div className="sidebar">
                <img src="/wikipathLogo.png" alt="Logo" className="App-logo" />

                {/* Dropdowns */}
                <select value={firstCategory} onChange={handleFirstCategoryChange}>
                    <option value="">Select First Category</option>
                    {/* Add options dynamically based on your data */}
                </select>
                {firstCategory && (
                    <select value={firstLink} onChange={(e) => setFirstLink(e.target.value)}>
                        <option value="">Select First Link</option>
                        {/* Add options dynamically based on your data */}
                    </select>
                )}

                <select value={secondCategory} onChange={handleSecondCategoryChange}>
                    <option value="">Select Second Category</option>
                    {/* Add options dynamically based on your data */}
                </select>
                {secondCategory && (
                    <select value={secondLink} onChange={(e) => setSecondLink(e.target.value)}>
                        <option value="">Select Second Link</option>
                        {/* Add options dynamically based on your data */}
                    </select>
                )}

                {/* Text */}
                <p>CHOOSE AN ALGORITHM:</p>

                {/* Buttons */}
                <button onClick={() => setSelectedAlgorithm('BFS')}>Breadth-First Search</button>
                <button onClick={() => setSelectedAlgorithm('DFS')}>Depth-First Search</button>
                <button onClick={handleGeneratePathClick} className="generate-path">GENERATE PATH</button>
                
                <div className="time-taken-box">
                    <timeTaken>Time Taken For Path:</timeTaken>
                    <div className="time-taken-value">{timeTaken} seconds</div>
                </div>
            </div>
            <div className="content">
                <GraphView />
            </div>
        </div>
    );
}

export default App;
