external import : string => unit = "require" [@@bs.val];

external importString : string => string = "require" [@@bs.val];

let identity x => x;
let truefn _ => true;
let falsefn _ => false;
