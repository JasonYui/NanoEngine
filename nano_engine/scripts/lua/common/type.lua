function TypeOf(obj)
    if (type(obj) == 'table') then
        return obj.__typeName;
    else
        return type(obj);
    end
end