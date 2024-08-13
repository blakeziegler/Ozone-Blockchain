val scala3Version = "3.4.2"

lazy val root = project
  .in(file("."))
  .settings(
    name := "ozone",
    version := "0.1.0-SNAPSHOT",
    scalaVersion := scala3Version,
    libraryDependencies += "org.scalameta" %% "munit" % "1.0.0" % Test,
    libraryDependencies += "com.squareup.okhttp3" % "okhttp" % "5.0.0-alpha.14",
    libraryDependencies += "org.apache.httpcomponents" % "httpcore" % "4.4.16",
    libraryDependencies += "org.scalaj" %% "scalaj-http" % "2.4.2" cross CrossVersion.for3Use2_13, // Use Scala 2.13 version
    libraryDependencies += "com.typesafe.akka" %% "akka-actor-typed" % "2.6.20",
    libraryDependencies += "com.typesafe.akka" %% "akka-stream" % "2.6.20",
    libraryDependencies += "com.typesafe.akka" %% "akka-http" % "10.5.3",
    libraryDependencies += "com.typesafe.akka" %% "akka-slf4j" % "2.6.20",
    libraryDependencies += "ch.qos.logback" % "logback-classic" % "1.4.11", // For SLF4J logging
    Compile / mainClass := Some("Main")
  )
