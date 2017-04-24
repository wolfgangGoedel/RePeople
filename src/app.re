Utils.import "style/app.css";

open ReactRe;

module App = {
  include Component.Stateful;
  let name = "App";
  type props = unit;
  type state = {people: Model.people};
  let getInitialState () => {people: []};
  let componentDidMount {setState} => {
    let setPeople p => setState (fun _ => {people: p});
    Backend.getPeople () |> Bs_promise.then_ setPeople |> ignore;
    None
  };
  let render {state: {people}} => {
    let person =
      switch people {
      | [person, ..._] => Some person
      | [] => None
      };
    <div className="App">
      <header> <AppBar /> </header>
      <main>
        (
          switch person {
          | Some p =>
            <PersonCard person=p />
          | None => ReactRe.nullElement
          }
        )
      </main>
    </div>
  };
};

include CreateComponent App;

let createElement = wrapProps ();