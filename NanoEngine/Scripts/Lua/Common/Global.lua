setmetatable(_G, {
    __newindex = function(table, key, value)
        local info = debug.getinfo(1, 'S');

        if (info == nil) then
            print(debug.traceback());
            return;
        end

        --[[ if (info.what ~= "main" and info.what ~= "C") then
            print(debug.traceback("attempt to define a variable out of main scrop " .. key));
            return;
        end ]]

        if (type(value) == "table" and rawget(value, "__type") == nil) then
            value.__type = key;
        end

        rawset(table, key, value);

    end,

    __index = function(table, key)
    end
})