const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
  entry: {
    main: './lib/js/src/main.js',
  },
  output: {
    path: path.join(__dirname, "build"),
    filename: 'bundle.js',
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: './public/index.html'
    }),
    new CopyWebpackPlugin([
      { from: './public' }
    ])
  ],
  module: {
    rules: [
      { test: /\.svg$/, use: 'file-loader' },
      { test: /\.css$/, use: [{ loader: 'style-loader' }, { loader: 'css-loader' }] },
      { exclude: [/\.html$/, /\.(js|jsx)(\?.*)?$/, /\.css$/, /\.json$/, /\.svg$/], use: 'url-loader' }
    ]
  },
  resolve: {
    modules: [path.resolve(__dirname, "src"), "node_modules"]
  }
};
