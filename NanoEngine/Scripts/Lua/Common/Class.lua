Object = {};
Object.__index = Object;

function Object:New()
end

function Object:Ctor()
end

local function CreateInstanceTemplate(class)
    return {
        __class = class,
        __type = class.__type
    };
end

local function CreateInstance(class, args)
    if (class == Object) then
        return Object;
    end

    local instance = {};
    local baseInstance = CreateInstance(class.__base);
    instance.__type = class.__type;
    instance.__index = instance;
    instance.__base = baseInstance;
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
        return CreateInstance(class, {...})
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