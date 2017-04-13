external import : string => unit = "require" [@@bs.val];

external importString : string => string = "require" [@@bs.val];

let withDefault render props children::(_: list ReactRe.reactElement) key::(_: option string)=? () =>
  render props;