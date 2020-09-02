#[macro_use]
extern crate clap;

fn main() {
    let matches = clap_app!(rusty_pass =>
        (version: "1.0")
        (author: "Nick M. <nmartin867@gmail.com>")
        (about: "Password Manager")
        (@arg CREATE: -n --new +takes_value "Creates a new entry")
        (@arg MODIFY: -m --edit +takes_value "Modifies an existing entry")
        (@subcommand test =>
            (about: "Manages sensitive information securely")
            (version: "1.0")
            (author: "Nick M. <nmartin867@gmail.com>")
            (@arg verbose: -v --verbose "Print test information verbosely")
        )
    ).get_matches();
}
