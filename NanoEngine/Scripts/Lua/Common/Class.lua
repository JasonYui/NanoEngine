Object = {};
Object.__index = Object;

function Object:New()
end

function Object:Ctor()
end

local function CreateInstanceTemplate(class, baseInstance)
    return {
        __type = class,
        __typeName = class.__typeName,
        __base = baseInstance,

        __index = function(table, key)
            print(class == table, table, table.__typeName, key);
            return table.__base[key] or table.__type[key];
        end
    };
end

local function CreateInstance(class, args)
    if (class == Object) then
        return Object;
    end

    local baseInstance = CreateInstance(class.__base);
    local instance = CreateInstanceTemplate(class, baseInstance);

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
    class.__typeName = nil;
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