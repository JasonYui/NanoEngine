function TypeOf(obj)
    if (type(obj) == 'table') then
        return obj.__type;
    else
        return type(obj);
    end
end