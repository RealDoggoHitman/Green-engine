local totaltime = 0.0

function Start()
    -- Create the object at the start
    model1 = createObject("Models/ceece.obj", "Textures/texture.png")
end

function Update(deltaTime)
    -- Update the total time (fix typo)
    totaltime = totaltime + deltaTime

    -- Calculate angle based on deltaTime
    local angle = totaltime * 2.0

    -- Rotation
    setRotation(model1, 0, math.sin(angle), math.cos(angle), 1)

    -- Radius for circular motion
    local radius = 3.0
    -- Position
    setPosition(model1, math.sin(angle) * radius, math.cos(angle) * radius, 0)

    -- Scale oscillation
    local scale = 1.0 + 0.5 * math.sin(totaltime * 3.0)
    -- Scale
    setScale(model1, scale, scale, scale)
end
