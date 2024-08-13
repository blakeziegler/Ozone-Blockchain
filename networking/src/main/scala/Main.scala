// Assuming Main.scala

import akka.actor.{ActorSystem, Props}

// Your custom classes and actors
import networking.{IPFSFetcher, IPFSdispatch, NodeActor}

case class TransactionData(data: String)

object Main extends App {

  val system = ActorSystem("BlockchainNetwork")

  // Step 2: Create node actors (representing nodes in the network)
  val node1 = system.actorOf(NodeActor.props, "node1")
  val node2 = system.actorOf(NodeActor.props, "node2")
  val nodes = Seq(node1, node2)

  // Step 3: Create the dispatcher actor
  val dispatcher = system.actorOf(IPFSdispatch.props(nodes), "dispatcher")

  // Step 4: Create the IPFS fetcher actor
  val ipfsFetcher = system.actorOf(IPFSFetcher.props(dispatcher), "ipfsFetcher")

  // Step 5: Send the initial IPFS hash to the IPFS fetcher to start the process
  val initialHash = "Qmf9z1ya8oDWj16eGPhgXmqcvd3qvBzoYULEzEvjTHkxYD"
  ipfsFetcher ! initialHash
}


