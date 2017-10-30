type person = {
  id: string,
  firstname: string,
  lastname: string,
  photoUrl: string,
  entity: string,
  email: string,
  phone: string,
  manager: option(string)
};

type people = list(person);

module Decode = {
  open Json.Decode;
  let person = (json) => {
    id: field("id", string) @@ json,
    firstname: field("firstname", string) @@ json,
    lastname: field("lastname", string) @@ json,
    photoUrl: field("photo", string) @@ json,
    entity: field("entity", string) @@ json,
    email: field("email", string) @@ json,
    phone: field("phone", string) @@ json,
    manager: optional(field("entity", string)) @@ json
  };
  let people = (json) => list(person) @@ json;
};
