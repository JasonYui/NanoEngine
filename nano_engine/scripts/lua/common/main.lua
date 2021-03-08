package.path = package.path .. ";c:/Code/NanoEngine/NanoEngine/Scripts/Lua/?.lua";

require("Common.GlobalMeta");
require("Common.Class");

Base = Class(Base);

function Base:Ctor()
    self.m_Name = "Base";
    self.m_Level = 1;
end

function Base:GetLevel()
    return self.m_Level;
end

Child = Class(Child, Base);

function Child:Ctor()
    self.m_Name = "Child";
    self.m_Sex = "Man";
end

function Child:GetName()
    return self.m_Name;
end

local child = Child:New();
print(child:GetLevel());