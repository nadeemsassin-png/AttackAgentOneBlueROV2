// 1. ENVIRONMENT: The grid and spatial data handler
CLASS MapEnvironment:
    METHOD Constructor(shpFilePath):
        PARSE shapefile (Geometry + Depth attributes)
        TRANSFORM spatial coords -> pixel grid (Scaling)
        CLASSIFY grid (Water=0, Land=1, Seam-Fixing)
    
    METHOD GetCellState(r, c): RETURN grid[r][c]
    METHOD IsPassable(r, c): RETURN grid[r][c] != LAND

// 2. UNIT LOGIC: The "Brain" of the ROV
CLASS ROV_Agent:
    PROPERTY position, heading, sensorRange
    METHOD Update(MapEnvironment):
        // Pathfinding or steering logic
        IF MapEnvironment.IsObstacleAhead():
            SteerAway()
        Move()

// 3. CORE SIMULATION ENGINE: The "Main.cpp"
CLASS SimulationManager:
    PROPERTY Map, UnitList
    
    METHOD Run():
        WHILE SimulationIsRunning:
            FOR EACH Unit IN UnitList:
                Unit.Update(Map)
            
            // Check for wins/losses/events
            ResolveInteractions(Map, UnitList)
            
            // Output for visualizer
            DrawFrame(Map, UnitList)