local totaltime = 0.0
local scaleFactor = 1.0
local colorShift = 0.0

function Start()
    model1 = createObject("Models/cube.obj", "Textures/texture.png")
end

function Update(deltaTime)
    -- Increase total time
    totaltime = totaltime + deltaTime * 20

    -- Rotate dynamically using sine waves
    local speedFactor = math.sin(totaltime * 0.1) * 50  -- Vary speed over time
    setRotX(model1, totaltime + speedFactor)
    setRotY(model1, totaltime - speedFactor)

    -- Pulsating scale effect
    scaleFactor = 1.0 + math.sin(totaltime * 0.2) * 0.3
    setScale(model1, scaleFactor, scaleFactor, scaleFactor)

    -- Dynamic color shifting
    colorShift = (math.sin(totaltime * 0.05) + 1) * 0.5  -- Normalize between 0 and 1
end
