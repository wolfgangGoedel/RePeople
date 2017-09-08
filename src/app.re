Utils.import "style/app.css";

type route =
  | DISCOVER
  | LISTALL;

type state = {
  people: Model.people,
  shown: route
};

let otherRoute =
  fun
  | LISTALL => "Discover"
  | DISCOVER => "Show All";

let peopleUpdater people {ReasonReact.state: state} => ReasonReact.Update {...state, people};

let shownUpdater _ {ReasonReact.state: state} =>
  ReasonReact.Update {
    ...state,
    shown:
      switch state.shown {
      | DISCOVER => LISTALL
      | LISTALL => DISCOVER
      }
  };

let onToggleClick self => self.ReasonReact.update shownUpdater;

let component = ReasonReact.statefulComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {people: [||], shown: LISTALL},
  didMount: fun self => {
    Js.Promise.(
      Backend.getPeople () |>
      then_ (
        fun people => {
          (self.update peopleUpdater) people;
          resolve ()
        }
      ) |> ignore
    );
    ReasonReact.NoUpdate
  },
  render: fun self => {
    let {people, shown} = self.state;
    let loaded = Array.length people > 0;
    <div className="App">
      <header> <AppBar shown=(otherRoute shown) onClick=(onToggleClick self) /> </header>
      <main>
        (
          if loaded {
            switch shown {
            | DISCOVER => <Discover people />
            | LISTALL => <ListAll people />
            }
          } else {
            ReasonReact.nullElement
          }
        )
      </main>
    </div>
  }
};
