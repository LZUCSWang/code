function [y] = gen_weightRecursive(a, b)
global nobj H w;
nobj = a;
H    = b;
a    = zeros(1, nobj);
d    = H;
w    = [];
produce_weight(a, 1, d)
y    = w;

function  produce_weight(a, i, d)
global nobj H w;
for k=0:d
      if i<nobj
          a(i) = k;
          d2   = d - k;
          produce_weight(a, i+1, d2);
      else
          a(i) = d;
          w = [w; a/H];
          break;
      end
end



