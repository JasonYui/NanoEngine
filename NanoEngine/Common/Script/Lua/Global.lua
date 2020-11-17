setmetatable(_G, {
    __newindex = function(table, key, value)
        debug.getinfo(1, 'S')
    end,

    __index = function(table, key)
    end
})