type people = array person
and person = {
  id: string,
  firstname: string,
  lastname: string,
  photoUrl: string,
  entity: string,
  email: string,
  phone: string,
  manager: option string
};

let jsonToPeople json => {
  let bindO f =>
    fun
    | Some x => f x
    | _ => None;
  let unwrapUnsafely =
    fun
    | Some v => v
    | None => raise (Invalid_argument "unwrapUnsafely called on None");
  let toPerson dict => {
    let decode key => key |> Js_dict.get dict |> bindO Js.Json.decodeString |> unwrapUnsafely;
    let decodeOpt key => key |> Js_dict.get dict |> bindO Js.Json.decodeString;
    {
      id: "id" |> decode,
      firstname: "firstname" |> decode,
      lastname: "lastname" |> decode,
      photoUrl: "photo" |> decode,
      entity: "entity" |> decode,
      email: "email" |> decode,
      phone: "phone" |> decode,
      manager: "manager" |> decodeOpt
    }
  };
  let decodePerson p => p |> Js.Json.decodeObject |> unwrapUnsafely |> toPerson;
  json |> Js.Json.decodeArray |> unwrapUnsafely |> Array.map decodePerson;
};
