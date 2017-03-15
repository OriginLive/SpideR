# How to contribute

I'm really glad you're reading this, because we need volunteer developers to help this project come to fruition.

If you haven't already, come find us in IRC ([#c++](irc://irc.rizon.net/c++) on rizon). We want you working on things you're excited about.

Here are some important resources:

  * [Our roadmap](https://github.com/OriginLive/SpideR/issues/1) is the 10k foot view of where we're going, and tells you where we are.
  * Mailing list: We're using irc to talk to eachother, no mailing list yet. Find us on rizon)
  * Bugs? [Issues](https://github.com/OriginLive/SpideR/issues) is where to report them
  * IRC: irc.rizon.net/c++ channel [#c++](irc://irc.rizon.net/c++). We're usually there during business hours. That's rizon, not freenode! Just ask about the project :)
  
## A small note
The project was originally coined as the SpideR, but later renamed to ReadeR, hence the confusion.
*ReadeR* is the current project's name

## Testing

We currently have an expert writing automated tests, those should be up soon.

## Submitting changes

Please send a [GitHub Pull Request to ReadeR](https://github.com/OriginLive/SpideR/pull/new/master) with a clear list of what you've done (read more about [pull requests](http://help.github.com/pull-requests/)). When you send a pull request, please use only finalized versions, which pass automated tests. For testing use your own dev branch. We can always use more test coverage. Please follow our coding conventions (below) and make sure all of your commits are atomic (one feature per commit).

Always write a clear log message for your commits. One-line messages are fine for small changes, but bigger changes should look like this:

    $ git commit -m "A brief summary of the commit
    > 
    > A paragraph describing what changed and its impact."

## Coding conventions

Start reading our code and you'll get the hang of it. We optimize for readability:

  * We use google coding standards [Google cpp](https://google.github.io/styleguide/cppguide.html)
  * We use everything the standard c++ library has to offer [cpp ref](http://en.cppreference.com/w/)
  * Everything that's not covered by the standard library comes with external libraries. We use those so we don't have to reinvent the wheel.
  * We're using the latest c++ standard to get the fastest speed and slickest code.
  * This is open source software. Consider the people who will read your code, and make it look nice for them. It's sort of like driving a car: Perhaps you love doing donuts when you're alone, but with passengers the goal is to make the ride as smooth as possible.
  * If you're unsure about anything, don't be afraid to ask.

Thanks,
Origin, The ReadeR project
