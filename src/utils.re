external import : string => unit = "require" [@@bs.val];

external importString : string => string = "require" [@@bs.val];

let identity x => x;

let truefn _ => true;

let falsefn _ => false;

let unwrap =
  fun
  | Some value => value
  | None => "";

let unwrapUnsafely =
  fun
  | Some v => v
  | None => raise (Invalid_argument "unwrapUnsafely called on None");

let bindO f =>
  fun
  | Some x => f x
  | _ => None;
