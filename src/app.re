Utils.import "style/app.css";

type state = {people: Model.people};

let component = ReasonReact.statefulComponent "App";

let make _children => {
  let updateState _state people => {people: people};
  let updateHandler people {ReasonReact.state: state} =>
    ReasonReact.Update (updateState state people);
  {
    ...component,
    initialState: fun () => {people: [||]},
    didMount: fun self => {
      Js.Promise.(
        Backend.getPeople () |>
        then_ (
          fun people => {
            (self.update updateHandler) people;
            resolve ()
          }
        ) |> ignore
      );
      ReasonReact.NoUpdate
    },
    render: fun {state} => {
      let {people} = state;
      
      <div className="App">
        <header> <AppBar /> </header>
        <main>
          (
            switch (Array.length people) {
            | 0 => ReasonReact.nullElement
            | _ => <Discover people />
            }
          )
        </main>
      </div>
    }
  }
};