print("Hello C++!")

whom = "C++"

function hello()
    print("Hello " .. whom .. "!")
end

function greetings(...)
    local args = { ... }
    local last_idx = #args

    local result = "Hello"

    for i, v in ipairs(args) do
        if i == last_idx then
            result = result .. " " .. v
        else
            result = result .. " " .. v .. ","
        end
    end
    return result
end

-- print(greetings("hallo", "jetzt", 2.0))

function dump_params(...)
    local results = {}
    for i, v in ipairs { ... } do
        results[i] = i .. ": " .. tostring(v) ..
            " [" .. type(v) .. "] "
    end
    return table.unpack(results)
end

-- print(dump_params("hello", 3.14, true, nil, "not shown")) -- table.unpack() stops at first nil value
-- print(dump_params("hello", 2.14, false, "shown"))

function table_size(T)
    local cnt = 0
    for _ in pairs(T) do
        cnt = cnt + 1
    end
    return cnt
end

pos = { x = 2, y = 4 }
seq = { 1, 4, 7 }

pr = require 'pl.pretty' -- use penlight for pretty printing
pr.dump(pos)
pr.dump(seq)

print("pos.size(): ", table_size(pos))
print("seq.size(): ", table_size(seq))
