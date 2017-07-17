Utils.import "style/app.css";

type state = {people: Model.people, shown: route}
and route =
  | DISCOVER
  | LISTALL;

let component = ReasonReact.statefulComponent "App";
let make _children => {
  let updatePeople state people => {...state, people};
  let peopleUpdater people {ReasonReact.state: state} =>
    ReasonReact.Update (updatePeople state people);

  let updateShown state shown => {...state, shown};
  let shownUpdater _ {ReasonReact.state: state} =>
      ReasonReact.Update (updateShown state (switch state.shown {
      | DISCOVER => LISTALL
      | LISTALL => DISCOVER
      }));

  let onToggleClick self => self.ReasonReact.update shownUpdater;
  
  let other currentRoute =>
      switch currentRoute {
      | LISTALL => "Discover"
      | DISCOVER => "All"
      };

  {
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
      
      <div className="App">
        <header>
          <AppBar shown=(other shown)
                onClick=(onToggleClick self) />
        </header>
        <main>
          (switch shown {
            | DISCOVER => {
                switch (Array.length people) {
                  | 0 => ReasonReact.nullElement
                  | _ => <Discover people />
                }
              }
            | LISTALL => <ListAll people />
            }
          )
        </main>
      </div>
    }
  }
};