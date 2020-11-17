package.path = package.path .. ";c:/Code/NanoEngine/NanoEngine/Scripts/Lua/?.lua";

require("Common.Global");
require("Common.Class");

Base = Class(Base);

function Base:Ctor()
    self.m_Name = "Base";
    self.m_Level = 1;
end

Child = Class(Child, Base);

function Child:Ctor()
    self.m_Name = "Child";
    self.m_Sex = "Man";
end

local child = Child:New();
print(child.m_Name, child.m_Sex, child.m_Level);