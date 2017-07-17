Utils.import "style/discover.css";

Random.self_init ();

type state = {
  currentPersonId: int,
  isPlaying: bool
};

module Fab = {
  let component = ReasonReact.statelessComponent "Fab";
  let make ::kind ::size=? ::onClick _children => {
    ...component,
    render: fun _ =>
      <a className=(
          "btn-default btn-floating waves-effect waves-light" ^ (
            switch size {
            | Some s => " btn-" ^ s
            | None => ""
            }
          )
        )
        onClick>
        <i className="material-icons"> (ReasonReact.stringToElement kind) </i>
      </a>
  };
};

let component = ReasonReact.statefulComponent "Discover";

let make people::people _children => {
  let updater isPlayingUpdater nextPersonId =>
    fun _ {ReasonReact.state: state} =>
      ReasonReact.Update {isPlaying: isPlayingUpdater state.isPlaying, currentPersonId: nextPersonId state.currentPersonId};
      
  let nextPersonUpdater f =>
    updater Utils.identity f;
  let playUpdater () =>
    updater Utils.truefn Utils.identity;
  let pauseUpdater () => 
    updater Utils.falsefn Utils.identity;

  let succ n => n == Array.length people - 1 ? 0 : n + 1;
  let pred n => n == 0 ? Array.length people - 1 : n - 1;

  let onNextClick self => self.ReasonReact.update (nextPersonUpdater succ);
  let onPrevClick self => self.ReasonReact.update (nextPersonUpdater pred);

  let timerId = ref None;

  let stopTimer self =>
    switch !timerId {
    | Some id => {
        Js.Global.clearInterval id;
        self.ReasonReact.update (pauseUpdater ()) ();
        timerId := None;
      };
    | None => ();
    };

  let onPauseClick self _ => {
    stopTimer self;
  };
  let onPlayClick self _ => {
    timerId := Some (Js.Global.setInterval (onNextClick self) 2000);
    onNextClick self ();

    self.ReasonReact.update (playUpdater ()) ();
  };

  {
    ...component,
    initialState: fun () => {currentPersonId: 0, isPlaying: false},
    willUnmount: fun self => {
      stopTimer self;
    },
    render: fun self => {
      <div className="Discover">
        <div className="card-container">
          <PersonCard person=people.(self.state.currentPersonId) />
        </div>
        <div className="fab-container">
          <Fab kind="skip_previous" onClick=(onPrevClick self) />
          (switch self.state.isPlaying {
          | true => <Fab kind="pause" size="large" onClick=(onPauseClick self) />
          | false => <Fab kind="play_arrow" size="large" onClick=(onPlayClick self) />
          })
          <Fab kind="skip_next" onClick=(onNextClick self) />
        </div>
      </div>
    }
  }
};