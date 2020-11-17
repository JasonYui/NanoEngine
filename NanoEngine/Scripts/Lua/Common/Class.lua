Object = {};
Object.__index = Object;

function Object:New()
    local instance = {};
    setmetatable(instance, Object);
    return instance;
end

function Object:Ctor()
end

function Object:Dtor()
end

function Object:CreateInstance(class, args)
    print(class.__type);
    if (class == Object) then
        return Object;
    end

    local instance = {};
    local baseInstance = Object:CreateInstance(class.__base);
    setmetatable(instance, baseInstance);

    if (args == nil) then
        class.Ctor(instance);
    else
        class.Ctor(instance, unpack(args));
    end

    return instance;
end

local function CreateClass(base)
    base = base or Object;

    local class = {};
    class.__index = class;
    class.__base = base;
    class.__type = nil;
    class.New = function (object, ...)
        return Object:CreateInstance(class, {...})
    end
    setmetatable(class, base);

    return class;
end

function Class(class, base)
    if (class ~= nil) then
        return class;
    end

    return CreateClass(base);
end