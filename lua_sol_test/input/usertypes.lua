-- usertype vec2d and operations defined in c++

local v1 = vec2d.new(1,2)
local v2 = vec2d.new(1.5,-2)
local v3 = vec2d.new(5,7.25)
local v7 = vec2d.new(v2)

print("v1:",v1)
print("v2:",v2)
print("v3:",v3)

local v4 = v1 + v2
print("v4:",v4)

if (v3 == v4) then
    print("v3 and v4 are equal")
end

v4 = -v4
print("v4:",v4)

local v5 = -v4
print("v5:",v5)

v6a = 3 * v5
v6b = v5 * 3
print("v6a:",v6a)
print("v6b:",v6b)

print("v7:",v7)

local v8 = e1_2d + e2_2d
print("v8:",v8)

--e1_2d = v7  -- that must not be possible!
              -- (=> need to manipulate global metatable to avoid it)
--print("e1_2d:",e1_2d)

local cplx1 = mvec2d_e.new(2,3)
local cplx2 = mvec2d_e.new(-1,1)
print("cplx1:", cplx1)
print("cplx2:", cplx2)
print("cplx1*cplx2 = ", cplx1*cplx2)
print("v1*v2 = ", v1*v2)
print("cplx1*v2 = ", cplx1 * v2)
print("v2*cplx1 = ", v2*cplx1)