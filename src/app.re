Utils.import "style/app.css";

type route =
  | DISCOVER
  | LISTALL;

type action =
  | ToggleShown
  | PeopleReceived Model.people;

type state = {
  people: Model.people,
  shown: route
};

let otherRoute =
  fun
  | LISTALL => "Discover"
  | DISCOVER => "Show All";

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {people: [||], shown: LISTALL},
  reducer: fun action state =>
    switch action {
    | ToggleShown =>
      ReasonReact.Update {
        ...state,
        shown:
          switch state.shown {
          | DISCOVER => LISTALL
          | LISTALL => DISCOVER
          }
      }
    | PeopleReceived people => ReasonReact.Update {...state, people}
    },
  didMount: fun self => {
    Backend.getPeople () |>
    Js.Promise.then_ (
      fun people => self.reduce (fun _ => PeopleReceived people) () |> Js.Promise.resolve
    ) |> ignore;
    ReasonReact.NoUpdate
  },
  render: fun self => {
    let {people, shown} = self.state;
    let loaded = Array.length people > 0;
    <div className="App">
      <header>
        <AppBar shown=(otherRoute shown) onClick=(self.reduce (fun _event => ToggleShown)) />
      </header>
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
